C Projects
git remote add origin https://github.com/ankit-kr-maurya-82/C-Projects.git

## Linux
└─$ gcc foodMenu.c<br>
./a.out<br>

# 🍽️ Food Order Management System (C Language)

A **menu-driven Food Order Management System** built using **C language**, demonstrating core programming concepts such as:
- Structures
- Functions
- File Handling (Binary files)
- Modular programming
- Menu-driven logic

This project simulates a restaurant-style ordering system with **Food, Drinks, Order History**, and **persistent storage**.

---

## 📌 Features

### ✅ Main Features
- Interactive **menu-driven interface**
- Food ordering based on **time (Morning / Afternoon / Evening)**
- Separate **Food & Drinks menus**
- Automatic **price calculation**
- **Order history tracking**
- **Persistent storage** using file handling (`orders.dat`)
- Grand total calculation
- Cross-platform screen clearing (Windows/Linux)

---

## 🧾 Order History
- All orders are saved in a binary file
- Orders persist even after program restart
- Corrupted data is automatically detected and cleaned
- Displays:
  - Category
  - Item Name
  - Price
  - Quantity
  - Total Amount

---

## 🗂️ Project Structure

Food-Order-Management/<br>
│
├── main.c # Main source code<br>
├── orders.dat # Binary file storing order history (auto-generated)<br>
├── README.md # Project documentation<br>


---

## 🧑‍🍳 Food Categories

### 🌅 Morning Menu
- Drinks
- Breakfast

### 🥪 Breakfast Items
- Sandwich
- Burger
- Omelette
- Noodles

### 🥤 Drinks
#### Hot Drinks
- Tea
- Coffee

#### Cold Drinks
- Carbonated Drinks
  - Cola
  - Lemon-Lime
  - Fruit Flavored
  - Ginger Ale
  - Sparkling Water
- Non-Carbonated Drinks
  - Juices
  - Shakes
  - Dairy-Based
  - Coconut Water

---

## 🛠️ Technologies Used

- **Language:** C
- **Compiler:** GCC / Turbo C / MinGW
- **Concepts Used:**
  - Structures
  - Arrays
  - Functions
  - File Handling (`fread`, `fwrite`)
  - Conditional statements
  - Loops

---

## ▶️ How to Run

### Step 1: Compile
```bash
gcc main.c -o food_order
