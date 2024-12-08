package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

func printArray(matrix [][]rune) {
	for i := 0; i < len(matrix); i++ {
		for j := 0; j < len(matrix[i]); j++ {
			if matrix[i][j] == 0 {
				fmt.Print("*")
			} else {
				fmt.Printf("%c",matrix[i][j])
			}
		}
		fmt.Println()
	}

}

type Direction int

const (
	Up		Direction = iota
	Right
	Down
	Left
)

func walk(matrix [][]rune, x int, y int, direction Direction) {
	// End, we hit the padding
	if x >= matrixLen-1 || y >= matrixLen-1 || x <= 0 || y <= 0 {
		return
	}

	xmatrix[x][y] = 'X'

	switch direction {
		case Up:
			if matrix[x-1][y] == '#' {
				walk(matrix,x,y, Right)
			} else {
				walk(matrix,x-1,y, direction)
			}
		case Right:
			if matrix[x][y+1] == '#' {
				walk(matrix,x,y, Down)
			} else {
				walk(matrix,x,y+1,direction)
			}
		case Down:
			if matrix[x+1][y] == '#' {
				walk(matrix,x,y, Left)
			} else {
				walk(matrix,x+1,y,direction)
			}
		case Left:
			if matrix[x][y-1] == '#' {
				walk(matrix,x,y,Up)
			} else {
				walk(matrix,x,y-1,direction)
			}
	}
}

// Only distinct steps need to be count, so simply count Xes
func countX(matrix [][]rune) (res int) {
	for i := 0; i < matrixLen; i++ {
		for j := 0; j < matrixLen; j++ {
			if matrix[i][j] == 'X' {
				res++
			}
		}
	}
	return res
}

var matrixLen int
var xmatrix [][]rune

func main() {
	var res int
	// XXX cheating here
	matrixLen = 130+2
	f, err := os.Open("input")
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)

	matrix := make([][]rune, matrixLen)
	xmatrix = make([][]rune, matrixLen)
	for i := 0; i < matrixLen; i++ {
		matrix[i] = make([]rune, matrixLen)
		xmatrix[i] = make([]rune, matrixLen)
	}

	row := 1
	startx, starty := 0,0

	for scanner.Scan() {
		line := scanner.Text()
		var pos int
		for i := 1; i < len(matrix[row])-1; i++ {
			matrix[row][i] = rune(line[pos])
			xmatrix[row][i] = rune(line[pos])
			if matrix[row][i] == '^' {
				startx = row
				starty = i
			}
			pos++
		}
		row++
	}

	walk(matrix,startx-1,starty, Up)
	//printArray(xmatrix)

	// + 1 since the logic doesn't count the first step
	res = countX(xmatrix) + 1

	fmt.Println("res: ", res)

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}

