Hello, guys. I'm Heinrich, a Ruby software engineer. 
today i developed a Bidding API (bellow) 

# Public Bidding API — Ruby + C++ Integration

## 📌 Project Description

This project is a RESTful API developed in Ruby (using Sinatra) with a native C++ extension, designed to meet the demands of public sector procurement processes. 
It allows suppliers to submit proposals for public contracts, view all submitted proposals, and rank them based on technical and financial criteria.

The ranking logic (value and deadline) is processed with high performance through a C++ module compiled and loaded via a native extension.

---

## 🚀 Technologies Used

- **Ruby 3.x**
- **Sinatra** (web framework)
- **C++** (native performance extension)
- **JSON** (communication format)
- **Make / extconf.rb** (to compile the extension)

---

## ⚙️ Features

- Submission of proposals for public contracts
- Listing of proposals by contract
- Automatic ranking via C++ module
- Modular structure for future expansion
- Project suitable for integration with ERPs or government portals



## 📂 Project Structure

├── api
│   └── biddingAPI.rb #main API in Ruby (Sinatra)
├── ext
│   └── Bid_ranker
│       ├── bidRanker.cpp #extensive native in C++ (ranking)
│       └── extconf.rb #build script for extensive 
└── lib
    └── bid_ranker.rb #wrapper ruby for C++ module
    


## 🛠️ Installation and Execution

### Prerequisites

- Ruby 3.x installed
- g++ or clang++
- Make (Linux/Mac) or MSYS (Windows)
- Bundler (optional)

### Steps to run locally

```bash
# 1. Compile the C++ extension
cd ext/Bid_ranker
ruby extconf.rb
make
cd ../../

# 2. Run the API
ruby api/biddingAPI.rb

# 3. Submit proposals
curl -X POST http://localhost:4567/bids \
  -H "Content-Type: application/json" \
  -d '{
        "contract_id": "1234",
        "supplier_id": "empresaXYZ",
        "amount": 45000,
        "deadline": 15
      }'

