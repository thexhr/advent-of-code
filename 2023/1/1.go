package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"unicode"
)

func main() {
	fmt.Println("Level 1")
	f, err := os.Open("input")
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)

	var line string
	var res int
	first, last := -1, -1

	for scanner.Scan() {
		line = scanner.Text()
		for c := range line {
			if unicode.IsDigit(rune(line[c])) {
				if first == -1 {
					first = int(line[c]) - 48
				}
				last = int(line[c]) - 48
			}
		}
		res += (first*10) + last
		//fmt.Println("line: ", line, "first: ", first, "last: ", last, "res: ", res)
		first = -1
		last = -1
	}

	fmt.Println("res: ", res)

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

}
