# Branch Sales Management System

A terminal-based sales tracking program written in C. This was a university assigned project for my Programming in C course.

## What it does

The program manages monthly sales data across multiple company branches. You tell it how many branches you have, enter the sales figures for each month, and it gives you a bunch of ways to analyze the data from there.

Here's what you can do from the menu:

- **Enter sales data** — input monthly sales for each branch, with validation that rejects invalid or negative values
- **Total sales** — see the overall revenue across all branches and months
- **Branch percentage** — see what share of total revenue each branch is responsible for
- **Peak month** — find out which month had the highest combined sales
- **Sort branches by month** — pick a month and get branches ranked from highest to lowest sales
- **Sort months by branch** — pick a branch and get its months ranked by performance

## Concepts used

- Structs to organize data (`branch` struct holding 12 months of sales)
- Dynamic memory allocation with `malloc` and `free`
- Bubble sort with index tracking to preserve branch/month labels after sorting
- Input validation loops with buffer clearing
- Modular design split across 7 functions

## How to compile and run

You need GCC installed.

```bash
gcc Project.c -o project
./project
```

On Windows:
```bash
gcc Project.c -o project.exe
project.exe
```

The program will ask you how many branches you want to track, then walk you through everything from the menu.

