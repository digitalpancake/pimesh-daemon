# PiNet Requirements

* Centralised User Accounts
* Network Install
* SD Card Flasher
* Backwards Compatibility
* Connect multiple separate PiMeshes
* Wireless and Wired Networks

# Hardware Requirements

* Minimum 1 Raspberry Pi 4/5
* 1 Server ( Running Linux )
* 1 SD Card Reader / Writer

# PiMesh Daemon Requirements

* Database ( Sqlite3 )
* User Accounts ( Kerberos )
* API -> For CLI and Web access
* File Storage ( Optional ) -> Point to Folder
* Remote Code Execution on clients
* Receive Files from clients

# Design

- Primary Languages ( C + Typescript )

* Long-running daemon on server ( FOSS )
* CLI for accessing daemon API ( FOSS )
* Web client for accessing daemon ( Closed Source )
* Pi Client ( FOSS )




### Client Software

* PiMesh Client
* Git
