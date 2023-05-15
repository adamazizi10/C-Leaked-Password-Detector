# CPP-Leaked-Password-Detector
# Leaked Password Detector
Leaked Password Detector is a command-line tool written in C++ that allows you to check whether your password has been leaked in a data breach.

## Requirements
Leaked Password Detector requires a C++ compiler, the `openssl` library, and the `curl` library to be installed on your system.

## Usage
To use Leaked Password Detector, follow these steps:

1. Compile the program by running the following command in your terminal:
```
g++ -o check_password check_password.cpp -lcurl -lssl -lcrypto
```
2. Run the program by typing the following command in your terminal:
```
./check_password <password>
```
Replace `<password>` with the password you want to check.

## Example
Here's an example of how to use Leaked Password Detector:

```
$ ./check_password password123
Your password has been found 20656 times in known data breaches. You should probably change your password!
```

## End of User Guide
