// test.fs
myVar = 10
5 |> double() |> print()         // Expected: 10
10 |> add(3) |> print()          // Expected: 13

range(1, 3) |> for each { double() |> print() } // Expected: 2, then 4

// --- Additional For Loop Tests ---
0 |> print() // Separator print

startRange = 2
endRange = 5 // Loop for 2, 3, 4
range(startRange, endRange) |> for each { double() |> print() } 
// Expected output: 4, 6, 8

0 |> print() // Separator print

range(5, 5) |> for each { 999 |> print() } // Should print nothing from the loop

0 |> print() // Separator print

// Reuse startRange = 2, endRange = 5 from above
range(startRange, endRange) |> for each { add(10) |> print() }
// Expected output: (2+10)=12, (3+10)=13, (4+10)=14
// --- End Additional For Loop Tests ---

myVar |> if > 5 {
  1 |> print()                     // Expected: 1
} else {
  0 |> print()                     // Expected: 0
}

3 |> if > 5 {
  100 |> print()                                  
} else {
  200 |> print()                   // Expected: 200
}

// Test a slightly longer chain
2 |> double() |> add(1) |> print() // Expected: (2*2)+1 = 5 