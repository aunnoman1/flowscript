// test.fs
myVar = 10
5 |> double() |> print()         // Expected: 10
10 |> add(3) |> print()          // Expected: 13

range(1, 3) |> for each { double() |> print() } // Expected: 2, then 4

if myVar > 5 {
  print(1)                     // Expected: 1
} else {
  print(0)
}

// Test piped if
3 |> if > 5 {
  print(100)                   // Expected: 100
} else {
  print(200)
}

// Test a slightly longer chain
2 |> double() |> add(1) |> print() // Expected: (2*2)+1 = 5 