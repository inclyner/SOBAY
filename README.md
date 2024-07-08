# SOBAY - Auction Management System

**Authors:**  
Francisco Carvalho (a2019129635)  
Maria Carrilho (a2019148211)  

**Academic Year:** 2022/2023

## Introduction

In this report, we present the architecture and operation of our practical work, describing and justifying the choices made throughout the development of this practical work.

## Development

### 1. System Description - SOBAY

The system named SOBAY manages an auction service. The program consists of three main files: the frontend, the backend, and the promoters.

- **Frontend:** The user logs in to the frontend via the command line. The backend validates the user's data. If the data is correct, the backend starts receiving commands from the user. Otherwise, it ignores any commands (excluding a new login attempt). Once authenticated, the user can sell products, bid in auctions, request the list of all items currently for sale, request the current time, check and load their balance. The user also receives information about their items, their bids, and when a promotion starts or ends.

- **Backend:** The backend has only one user, who is the administrator. Unlike the frontend, the backend has only one instance running during the program's execution. It serves as the connection between all other frontends and promoters in execution.

### 2. Data Structures

Currently, we have two main structures:

- **Linked list of items:** Where we store the items.
  - `item` structure: Stores the ID, name, category, base value, "buy now" value, the user selling, the auction duration, the user who bought, and the pointer to the next item.
  
- **Authenticated users structure:**
  - `user` structure: Stores the process PID and the user's username.

### 3. Environment Variables

The environment variables are only read by the backend and are obtained using the `getenv()` method.

- **FUSERS:** Variable that stores the name of the file where users are registered in the format `username password balance`.
- **FPROMOTORS:** Variable that stores the name of the file where the promoters' executables are stored.
- **FITEMS:** Variable that stores the name of the file with information about the items that were still on auction when the platform was closed.

### 4. Library Provided by the Instructors

The library provided by the instructors handles reading and safeguarding user data in a file. This library opens the `users.txt` file (using the environment variable `FUSERS`). Once the file is opened, we have access to all information about a given user and it also allows the validation of user login data.

## How to Execute

1. Ensure that all necessary environment variables are correctly set:
   - `FUSERS`
   - `FPROMOTORS`
   - `FITEMS`

2. Compile and run the backend.

3. Compile and run the frontend.

4. Log in through the frontend and start interacting with the auction system.

## Dependencies

- Data reading library provided by the instructors.
- C compiler (gcc or other compatible).
- Unix-based operating system (Linux, macOS).

## Final Notes

This project was developed as part of the Operating Systems course, academic year 2022/2023. All architectural choices were made aiming at simplicity and efficiency in auction management.

