FROM linuxserver/code-server:version-v3.5.0
LABEL maintainer="Brad Larson"

RUN apt-get update
RUN apt-get install -y curl wget systemd
RUN apt-get install -y libsm6 libxext6 ffmpeg

WORKDIR /app
ENV LANG C.UTF-8

# debugger port
EXPOSE 3000 
# node port
EXPOSE 5000
# vscode port
EXPOSE 8443 

RUN code-server --install-extension ms-python.python
RUN code-server --install-extension platformio.platformio-ide
RUN code-server --install-extension eamodio.gitlens
#RUN code-server --install-extension ms-vscode-remote.remote-ssh

# Launch shell script
#CMD ["systemctl", "enable", "--auth none","--now code-server@$USER"]
#RUN ["/bin/bash"]