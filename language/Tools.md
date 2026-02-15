# More tools
#### Deployment of other development tools
``` shell
sudo xbps-install -uy gcc cmake make patch
```
#### Install the lock screen tool i3-lock
``` shell
cd /data/git && git clone https://github.com/Raymo111/i3lock-color.git && cd i3lock-color
./build.sh
./install-i3lock-color.sh
```
#### Install the container component Docker
``` shell
sudo xbps-install -uy docker docker-compose
sudo mkdir -p /etc/docker
vim /etc/docker/daemon.json
ln -s /etc/sv/containerd  /etc/runit/runsvdir/default/containerd
ln -s /etc/sv/docker /etc/runit/runsvdir/default/docker
sv status containerd
sv status docker
```
#### Install container application Flatpak
``` shell
su $USER
flatpak remote-add --if-not-exists --user flathub https://dl.flathub.org/repo/flathub.flatpakrepo
flatpak remote-modify flathub --url=https://mirrors.ustc.edu.cn/flathub
flatpak remotes --show-details
flatpak install -y com.tencent.WeChat #file path： $HOME/.var/app/com.tencent.WeChat/xwechat_files
flatpak install -y cn.wps.wps_365
flatpak install -y com.github.gmg137.netease-cloud-music-gtk
flatpak list # show application list
```
#### Install and deploy a KVM virtualization environment
``` shell
sudo xbps-install -uy libvirt virt-manager qemu bridge-utils dnsmasq
ln -s /etc/sv/libvirtd /etc/runit/runsvdir/default/libvirtd
ln -s /etc/sv/virtlogd /etc/runit/runsvdir/default/virtlogd
sudo cp app/virtual-conf/50-libvirt.rules /etc/polkit-1/rules.d
sudo usermod -a -G libvirt $USER
sudo usermod -a -G libvirt root
sudo usermod -a -G kvm $USER
sudo usermod -a -G kvm root
sv restart libvirtd
sv restart virtlogd
# networks path: " /etc/libvirt/qemu/networks/autostart "
# delete default network
sudo virsh net-destroy default
sudo virsh net-undefine default # all delete
# create virtual network
sudo cp app/virtual-conf/10-vlan.xml /etc/libvirt/qemu/networks
sudo virsh net-define /etc/libvirt/qemu/networks/10-vlan.xml
sudo virsh net-autostart vlan10
sudo virsh net-start vlan10
# show all network
sudo virsh net-list --all
sudo virsh net-dumpxml vlan10 # test
# the system ISO files path: " /var/lib/libvirt/images "
# https://fedorapeople.org/groups/virt/virtio-win/direct-downloads/archive-virtio/
sudo virsh list # show run virtual host
sudo virsh net-dhcp-leases vlan10 # View virtual machines connected via DHCP under the virtual network
```
