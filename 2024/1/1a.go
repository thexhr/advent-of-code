package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strconv"
	"strings"
)

func findOccurences(a int, b []int) (n int) {
	for _, v := range b {
		if v == a {
			n++
		}
		// array is sorted
		if v > a {
			break
		}
	}
	return n
}

func main() {
	f, err := os.Open("input")
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)

	var res int
	var left []int
	var right []int

	for scanner.Scan() {
		line := scanner.Text()
		//fmt.Println(line)
		erg := strings.Fields(line)
		l, _ := strconv.Atoi(erg[0])
		r, _ := strconv.Atoi(erg[1])
		left = append(left, l)
		right = append(right, r)
	}

	sort.Ints(left[:])
	sort.Ints(right[:])

	if len(left) != len(right) {
		log.Fatal("Arrys have different length")
	}

	for _, l := range left {
		res += (l * findOccurences(l, right))
	}

	fmt.Println("res: ", res)

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
