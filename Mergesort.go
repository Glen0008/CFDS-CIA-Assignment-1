package main

import (
	"fmt"
	"math/rand"
	"runtime"
	"time"
)

// Merge function
func merge(left, right []int) []int {
	result := make([]int, 0, len(left)+len(right))
	i, j := 0, 0
	for i < len(left) && j < len(right) {
		if left[i] <= right[j] {
			result = append(result, left[i])
			i++
		} else {
			result = append(result, right[j])
			j++
		}
	}
	result = append(result, left[i:]...)
	result = append(result, right[j:]...)
	return result
}

// MergeSort function
func mergeSort(arr []int) []int {
	if len(arr) <= 1 {
		return arr
	}
	mid := len(arr) / 2
	left := mergeSort(arr[:mid])
	right := mergeSort(arr[mid:])
	return merge(left, right)
}

func main() {
	// Prepare large input (100,000 random integers)
	size := 100000
	arr := make([]int, size)
	for i := 0; i < size; i++ {
		arr[i] = rand.Intn(size * 10)
	}

	// Record initial memory usage
	var memStart runtime.MemStats
	runtime.ReadMemStats(&memStart)

	// Record start time (wall clock) and CPU time
	startWall := time.Now()
	startCPU := time.Now()

	// Run Merge Sort
	arr = mergeSort(arr)

	// Record end times
	endWall := time.Since(startWall)
	endCPU := time.Since(startCPU)

	// Record final memory usage
	var memEnd runtime.MemStats
	runtime.ReadMemStats(&memEnd)

	// Output metrics
	fmt.Println("Sorted first 10 numbers:", arr[:10])
	fmt.Println("Execution Time (Wall Clock):", endWall)
	fmt.Println("CPU Time:", endCPU)
	fmt.Printf("Memory Usage: %.2f MB\n", float64(memEnd.Alloc-memStart.Alloc)/(1024*1024))
}
