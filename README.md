# ag-radius
Access Gateway Radius Library

This repository is to create a Radius Client library. This library can be linked to Access Gateway.

Pre-requisites for this library are `radcli`

This library can be created in the following two different ways

## Directly on the VM (or Linux box)

1. Pull this [repository](https://github.com/krishnakumar3044/ag-radius)

2. Go to directory srcDir/external/radcli
   - Execute the following commands
     - `tar -xvzf radcli-1.2.10.tar.gz`
     - Go to directory `srcDir/external/radcli/radcli-1.2.10`
     - `./configure`
     - `make`
     - `make install` 
        ( creates files /usr/local/lib/libradcli.so directory and /usr/local/include/radcli/radcli.h)

3. Create a directory `build` and go to `build' directory

4. Run the following commands
   - `cmake ..`
   - `make` 
   - `make install` (make sure to run as `root`). This will create the following files
     - `/etc/agrc/radiusclient.conf`
     - `/etc/agrc/dictionary`
     - `/etc/agrc/dictionary.nomadix`
     - `/etc/agrc/dictionary.wba
     - `/etc/agrc/servers`
     - `/usr/local/lib/libaccess-gateway-radius-client-lib.so`
     - `/usr/local/include/AccessGatewayRadiusClient.h`
     
   - Run the sample program from `build` directory (app/agrcbin) - to ensure that everything is installed properly     
     (This sample program includes /usr/local/include/AccessGatewayRadiusClient.h and links to libaccess-gateway-radius-client-lib.so) 
     
  5. Please do the following in your application
     - Include header file `/usr/local/include/AccessGatewayRadiusClient.h`
     - Link your executable to library - `libaccess-gateway-radius-client-lib.so`
    
## Using a Docker Container

1. Pull this [repository](https://github.com/krishnakumar3044/ag-radius)

2. Pre-requisites are handled in Dockerfile. 
   - Execute `srcDir/build.sh` file - To create Docker image
   - Execute `srcDir/run.sh` - To start a container using the Docker image

3. You will be in /ag-radius directroy
   - Create a directory `build` and go to `build' directory
   - `cmake ..`
   - `make` 
   - `make install` (make sure to run as `root`). This will create the following files
     - `/etc/agrc/radiusclient.conf`
     - `/etc/agrc/dictionary`
     - `/etc/agrc/dictionary.nomadix`
     - `/etc/agrc/dictionary.wba
     - `/etc/agrc/servers`
     - `/usr/local/lib/libaccess-gateway-radius-client-lib.so`
     - `/usr/local/include/AccessGatewayRadiusClient.h`
   
   - Run the sample program from `build` directory (app/agrcbin) - to ensure that everything is installed properly    

