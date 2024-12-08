package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

const (
	Up	int = iota
	Down
	Left
	Right
	UpperLeft
	UpperRight
	LowerLeft
	LowerRight
)

func checkForXmas(matrix [][]rune, xmas []rune, x,y,direction int) bool {
	ptr := 1
	switch direction {
		case Up:
			for _, v := range xmas {
				c := matrix[x-ptr][y]
				if c != v {
					return false
				}
				ptr++
			}
		case Down:
			for _, v := range xmas {
				c := matrix[x+ptr][y]
				if c != v {
					return false
				}
				ptr++
			}
		case Left:
			for _, v := range xmas {
				c := matrix[x][y-ptr]
				if c != v {
					return false
				}
				ptr++
			}
		case Right:
			for _, v := range xmas {
				c := matrix[x][y+ptr]
				if c != v {
					return false
				}
				ptr++
			}
		case UpperLeft:
			for _, v := range xmas {
				c := matrix[x-ptr][y-ptr]
				if c != v {
					return false
				}
				ptr++
			}
		case UpperRight:
			for _, v := range xmas {
				c := matrix[x-ptr][y+ptr]
				if c != v {
					return false
				}
				ptr++
			}
		case LowerLeft:
			for _, v := range xmas {
				c := matrix[x+ptr][y-ptr]
				if c != v {
					return false
				}
				ptr++
			}
		case LowerRight:
			for _, v := range xmas {
				c := matrix[x+ptr][y+ptr]
				if c != v {
					return false
				}
				ptr++
			}
		default:
			return false
	}
	return true
}

func main() {
	var res int
	f, err := os.Open("input")
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	// XXX do not cheat here by hard coding the array's length
	matrixLen := 140+3+3
	scanner := bufio.NewScanner(f)

	matrix := make([][]rune, matrixLen)
	for i := 0; i < matrixLen; i++ {
		matrix[i] = make([]rune, matrixLen)
	}

	row := 3
	for scanner.Scan() {
		line := scanner.Text()
		var pos int
		for i := 3; i < len(matrix[row])-3; i++ {
			matrix[row][i] = rune(line[pos])
			pos++
		}
		row++
	}

	xmas := []rune{'M', 'A', 'S'}
	samx := []rune{'A', 'M', 'X'}

	for x := 0; x < matrixLen; x++ {
		for y := 0; y < matrixLen; y++ {
			// Skip over padding
			if matrix[x][y] == 0 {
					continue
			}
			c := matrix[x][y]
			if c == 'X' {
				for d := 0; d < 8; d++ {
					if checkForXmas(matrix, xmas, x, y, d) == true {
						res++
					}
				}
			} else if c == 'Y' {
				for d := 0; d < 8; d++ {
					if checkForXmas(matrix, samx, x, y, d) == true {
						res++
					}
				}
			}
		}
	}

	fmt.Println("res: ", res)

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}

