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

	x := make(map[int]int)

	for scanner.Scan() {
		line := scanner.Text()
		//fmt.Println(line)
		erg := strings.Fields(line)
		l, _ := strconv.Atoi(erg[0])
		r, _ := strconv.Atoi(erg[1])
		left = append(left, l)
		right = append(right, r)
		x[r]++;
	}

	sort.Ints(left[:])
	sort.Ints(right[:])

	for _, l := range left {
		res += (l * x[l])
	}

	fmt.Println("res: ", res)

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
