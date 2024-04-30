package main

import (
	"fmt"
	"os"
)

func main() {
	if len(os.Args) == 1 {
		fmt.Println("Read more about swagr at https://github.com/TheWisePigeon/swagr")
		os.Exit(0)
	}
	run(os.Args)
}

func run(args []string) int {
	switch args[1] {
	case "init":
		handleInitCMD()
	case "serve":
		handleServeCMD()
	default:
		fmt.Println("Read more about swagr at https://github.com/TheWisePigeon/swagr")
	}
	return 0
}

func handleServeCMD() {

}

func handleInitCMD() {

}
