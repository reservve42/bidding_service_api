Hi mates. I'm Heanrig, a software engineer. today I developed a Bidding API (bellow) 

# Public Bidding API — Ruby + C++ Integration

## 📌 Project Description

This project is a RESTful API developed in Ruby (using Sinatra) with a native C++ extension, designed to meet the demands of public sector procurement processes. 
It allows suppliers to submit proposals for public contracts, view all submitted proposals, and rank them based on technical and financial criteria.

The ranking logic (value and deadline) is processed with high performance through a C++ module compiled and loaded via a native extension.

---

## 🚀 Technologies Used

- **Ruby 3.x**
- **Sinatra** (web framework)
- **C++** (native performance extension, but you can use C++ 11/14/17/21)
- **JSON** (communication format)
- **Make / extconf.rb** (to compile the extension)

---


```
## 📂 You maybe see this structure in your project. If yes, probably you did the same way like me

- ├── api
- │   └── biddingAPI.rb #main API in Ruby (Sinatra)
- ├── ext
- │   └── Bid_ranker
- │       ├── bidRanker.cpp #extensive native in C++ (ranking)
- │       └── extconf.rb #build script for extensive 
- └── lib
-      └── bid_ranker.rb #wrapper ruby for C++ module
    
```

## 🛠️ Installation and Execution

### Prerequisites

- Ruby 3.x installed or use RVM for most current version, I recommend use RVM
- g++ or clang++
- Make (Linux/Mac) or MSYS (Windows)
- Bundler 

### Steps to run locally

```zsh
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
        "supplier_id": "companyXYZ",
        "amount": 45000,
        "deadline": 15
      }'

