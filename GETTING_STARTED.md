# Message Queue Creation Program (message_create.c)

The following C program facilitates the creation of System V message queues. It provides flexibility in specifying the key for the message queue through various options. Additionally, it allows setting flags such as `IPC_CREAT` and `IPC_EXCL`, as well as defining permissions for the message queue.

## Usage

```bash
./message_queue_creator [-cx] {-f pathname | -k key | -p} [octal-perms]

```

## Options and Arguments

    -c: Use IPC_CREAT flag. This flag is used to create a new message queue if it does not already exist.
    
    -x: Use IPC_EXCL flag. When combined with IPC_CREAT, it ensures that the message queue is created exclusively, failing if it already exists.
    
    -f pathname: Generate key using ftok() with the provided pathname. ftok() converts a pathname and a project identifier into a System V IPC key.
    
    -k key: Use the specified key as the key. The key is a unique identifier for the message queue.
    
    -p: Use IPC_PRIVATE key. This creates a private message queue, where the system generates a unique key for the queue.
    
    octal-perms: Optional octal permissions for the message queue.

## Example Usage
    
### Create a message queue using `IPC_CREAT` flag with default permissions
```bash
./message_queue_creator -c -f /path/to/file
```

### Create a message queue with a specific key and set permissions
```bash
./message_queue_creator -k 12345 0644
```

### Create a private message queue with custom permissions
```bash
./message_queue_creator -p 0755
```
Note: Ensure proper permissions and error handling are implemented based on your specific use case.

# Message Sending Program (message_send.c)

The following C program facilitates the insertion of messages into a System V message queue. It allows users to specify the message queue ID (`msqid`), message type (`msg-type`), and the content of the message (`msg-text`). Additionally, users can utilize the `-n` parameter to set the `IPC_NOWAIT` flag, which indicates that the message should not be sent if the message queue is full, and the program should not wait.

## Usage

```bash
./message_send [-n] msqid msg-type [msg-text]
```

## Options and Arguments

    -n: Sets the IPC_NOWAIT flag, indicating that the message should not be sent if the message queue is full, and the program should not wait.
    
    msqid: Message queue ID.
    
    msg-type: Message type.
    
    msg-text: Optional message text.
    
## Usage Example

```bash
# Send a message with IPC_NOWAIT flag
./message_send -n 3 20 Hello
```
Note: Ensure the message queue ID (msqid) and message type (msg-type) are provided, and handle the optional message text appropriately based on your use case.

# Message Receiving Program (message_receive.c)

This C program is designed to receive the next message from a System V message queue. Users can specify the message queue ID (`msqid`), and optionally, the maximum number of bytes to receive (`max-bytes`). Additionally, users can utilize various options to control the behavior of the message reception.

## Usage

```bash
./message_receive [options] msqid [max-bytes]
```

## Options and Arguments

    -e: Set the MSG_NOERROR flag. This flag ensures that the message is received even if it would overflow the message queue.
    
    -n: Set the IPC_NOWAIT flag. This flag indicates that the message should not be received if the message queue is empty, and the program should not wait.
    
    -t type: Specify the type of the received message.
    
    -x: Set the MSG_EXCEPT flag. This flag is used to receive the first message that does not match the specified type.
    
## Example Usage

```bash
# Receive a message with IPC_NOWAIT flag and a maximum of 1024 bytes
./message_receive -n 0 1024
```

Note: Ensure the message queue ID (msqid) is provided, and handle the optional maximum number of bytes (max-bytes) appropriately based on your use case.
