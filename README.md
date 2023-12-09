# Linux Message Queues CLI Utilities

Welcome to the Linux Message Queues CLI Utilities repository! Elevate your inter-process communication game with this collection of command-line tools implemented in C, designed to seamlessly create, send, and receive messages using message queues in the Linux operating system.

## Why Message Queues in Linux?

Unlock the potential of efficient data exchange between processes using the powerful `msgget()` system call. Dive into the world of key features:

- **Key Generation:** Leverage the `key_t` parameter, generated with `IPC_PRIVATE` or `ftok()`, as a unique identifier for your message queues.

- **Permission Bits:** Tailor your queue with the `msgflag` parameter, specifying permission bits, including options like `IPC_CREAT` for creating a new queue and `IPC_EXCL` for exclusive creation.

- **Dynamic Communication:** Facilitate structured communication between processes with message queues, providing an elegant solution for sending and receiving messages.

## Repository Highlights:

Embark on a journey through a curated collection of C-based command-line utilities, each a testament to different facets of message queue manipulation and functionality. From creating queues to sending and receiving messages, these programs are your go-to resource for mastering Linux message queues.

## Getting Started:

Clone this repository to your local environment and explore the intuitive CLI utilities. Utilize the provided compilation commands to seamlessly run the programs, experiencing firsthand the prowess of inter-process communication through message queues.

## Repository Contents:

- **message_create.c:** Command-line utility illustrating the creation of a new message queue using the `msgget()` call.
- **message_send.c:** CLI tool demonstrating the art of sending messages through a message queue.
- **message_receive.c:** Command-line program showcasing how to adeptly receive messages from a message queue.

## Installation
- **Clone the Repository:**
```shell
git clone https://github.com/AdarkSt/Linux-Message-Queues-CLI.git
cd Linux-Message-Queues-CLI
```
- **Move Executables to a Directory in PATH:**
```shell
sudo cp message_create message_send message_receive /usr/local/bin/
```
- **Set Execute Permissions:**
```shell
chmod +x /usr/local/bin/message_create /usr/local/bin/message_send /usr/local/bin/message_receive
```
- **Usage**
```shell
message_create 
Exactly one of the options -f, -k, -p must be supplied
Usage: message_create [-cx] {-f pathname | -k key | -p} [octal-perms]
-c Use IPC_CREATE flag
-x Use IPC_EXCL flag
-f Use pathname to Generate key using ftok()
-k key Use key as key
-p Use IPC_PRIVATE key
```

## Contributions:

Become a part of the journey! Feel empowered to contribute to this repository by adding your CLI utilities or enhancing the existing ones. Let's collaboratively build a comprehensive resource for mastering Linux message queues through elegant and efficient command-line tools.
