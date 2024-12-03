package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"regexp"
	"strconv"
)

func main() {
	f, err := os.Open("input")
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)

	var res int

	m := `do\(\)|don't\(\)|mul\(\d+,\d+\)`
	r, _ := regexp.Compile(m)

	do := true

	for scanner.Scan() {
		var a,b int
		line := scanner.Text()
		match := r.FindAllString(line, -1)
		for _, v := range match {
			if v == "do()" {
				do = true
				continue
			} else if v == "don't()" {
				do = false
				continue
			}
			if do == false {
				continue
			}
			re, _ := regexp.Compile(`(\d)+`)
			m2 := re.FindAllString(v, -1)

			a,_ = strconv.Atoi(m2[0])
			b,_ = strconv.Atoi(m2[1])
			res += a * b
		}
	}

	fmt.Println("res: ", res)

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
