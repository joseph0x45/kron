package main

import (
	"bufio"
	"embed"
	"encoding/json"
	"fmt"
	"log"
	"net"
	"net/http"
	"os"
	"strings"

	"github.com/a-h/templ"
	"golang.org/x/crypto/bcrypt"
)

type Doc struct {
	Name   string `json:"name"`
	Path   string `json:"path"`
	Public bool   `json:"public"`
}

type baseConfig struct {
	Docs    []Doc  `json:"documentations"`
	PassKey string `json:"passkey"`
}

//go:embed static/*
var staticFS embed.FS

func errorOut(err error, msg string) {
	fmt.Println(msg)
	fmt.Println(err)
	os.Exit(1)
}

func writeConfig(cfg *baseConfig) {
	bytes, err := json.MarshalIndent(cfg, "", " ")
	if err != nil {
		errorOut(err, "Error writing config file")
	}
	f, err := os.OpenFile("./.hub.config.json", os.O_WRONLY, 777)
	if err != nil {
		errorOut(err, "Error writing config file")
	}
	defer f.Close()
	_, err = f.Write(bytes)
	if err != nil {
		errorOut(err, "Error writing config file")
	}
}

func main() {
	args := os.Args
	if len(args) >= 2 {
		cmd := args[1]
		switch cmd {
		case "init":
			cfg := &baseConfig{
				Docs: []Doc{},
			}
			f, err := os.Create("./.hub.config.json")
			if err != nil {
				errorOut(err, "Error while creating config file")
			}
			defer f.Close()
			bytes, err := json.MarshalIndent(cfg, "", " ")
			if err != nil {
				errorOut(err, "Error while creating config file")
			}
			_, err = f.Write(bytes)
			if err != nil {
				errorOut(err, "Error while creating config file")
			}
			fmt.Println("Config file created")
			return
		case "new":
		case "passkey":
			subCmd := args[2]
			switch subCmd {
			case "new":
				config := &baseConfig{}
				f, err := os.Open("./.hub.config.json")
				if err != nil {
					errorOut(err, "Error reading config file")
				}
				err = json.NewDecoder(f).Decode(config)
				if err != nil {
					fmt.Println("Error reading config file")
					fmt.Println(err)
					os.Exit(1)
				}
				if config.PassKey != "" {
					reader := bufio.NewReader(os.Stdin)
					fmt.Println("You already set a passkey. Would you like to overwrite it? y/n (default yes)")
					choice, err := reader.ReadByte()
					if err != nil {
						errorOut(err, "Error reading your answer")
					}
					//Consume remaining data in buffer
					reader.ReadString('\n')
					switch choice {
					//ASCII values of n and N
					case 78, 110:
						fmt.Println("Aborting passkey creation")
						return
					default:
						fmt.Println("Enter your new passkey >")
						passkey, err := reader.ReadString('\n')
						if err != nil {
							errorOut(err, "Error reading your answer")
						}
						passkey = strings.TrimSpace(passkey)
						hash, err := bcrypt.GenerateFromPassword([]byte(passkey), bcrypt.DefaultCost)
						if err != nil {
							errorOut(err, "Error while hasing your passkey")
						}
						config.PassKey = string(hash)
						writeConfig(config)
						fmt.Println("Passkey updated")
					}
				}
			}
		}
		return
	}

	fs := http.FS(staticFS)
	fileServer := http.FileServer(fs)

	r := http.NewServeMux()

	r.Handle("GET /", templ.Handler(HomePage()))

	r.HandleFunc("GET /{file}", func(w http.ResponseWriter, r *http.Request) {
		file := r.PathValue("file")
		switch file {
		case "docs":
			http.ServeFile(w, r, "static/index.html")
		default:
			_, err := fs.Open(file)
			if err != nil {
				http.NotFound(w, r)
				return
			}
			fileServer.ServeHTTP(w, r)
		}
		return
	})
	server := &http.Server{
		Addr:    net.JoinHostPort("0.0.0.0", "8081"),
		Handler: r,
	}
	log.Println("Server started on port 8081")
	err := server.ListenAndServe()
	if err != nil {
		panic(err)
	}
}
