package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"

	//"strconv"
	"strings"
)

func ordered(line []string) bool {
	var a int
	var b int
	var asc bool
	a,_ = strconv.Atoi(line[0])
	b,_ = strconv.Atoi(line[1])

	if a < b {
		asc = true
	} else {
		asc = false
	}

	for i := 0; i < len(line)-1; i++ {
		a,_ = strconv.Atoi(line[i])
		b,_ = strconv.Atoi(line[i+1])
		if asc && a > b {
			return false
		} else if !asc && a < b {
			return false
		}
	}
	return true
}

func main() {
	f, err := os.Open("input")
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)

	var safeReports int
	for scanner.Scan() {
		var safe int
		line := strings.Fields(scanner.Text())
		for i := 0; i < len(line); i++ {
			var a int
			var b int
			if !ordered(line) {
				break
			}

			if i == len(line)-1 {
				a,_ = strconv.Atoi(line[i-1])
				b,_ = strconv.Atoi(line[i])
			} else {
				a,_ = strconv.Atoi(line[i])
				b,_ = strconv.Atoi(line[i+1])
			}

			calc := max(a,b) - min(a,b)
			if calc != 0 && calc <= 3 {
				safe++
			}
		}
		if safe == len(line) {
			safeReports++
		}
		safe = 0
	}

	fmt.Println("res: ", safeReports)

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
