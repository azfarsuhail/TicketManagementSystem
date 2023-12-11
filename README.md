# Ticket Reservation System

This repository contains a basic implementation of a ticket reservation system in C++. It includes:

## Abstract Base Class
- `ITicket`: An abstract base class defining interfaces for ticket operations.

## Concrete Class
- `Ticket`: A concrete class implementing the `ITicket` interface, representing a ticket with details like passenger information, seat, departure, destination, price, and cancellation status.

## Reservation System
- `ReservationSystem`: A class managing booking, cancellation, and retrieval of ticket information. It uses an array of `Ticket` objects.

## Usage
- The `main()` function acts as the user interface for interacting with the reservation system.
- Options include booking a ticket, canceling a ticket by number, retrieving ticket information, and viewing available tickets.

## Instructions
- The program prompts users for input to perform various actions such as ticket booking or cancellation.

## How to Use
- Compile the code and execute the resulting binary to interact with the reservation system.
- Follow the on-screen prompts to perform actions like booking, canceling, and retrieving ticket information.

