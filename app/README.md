# Applications
### i3lock-colors
``` bash
git clone https://github.com/Raymo111/i3lock-color.git && cd i3lock-color
sudo chmod +x i3lock-devel && bash i3lock-devel
./build.sh
./install-i3lock-color.sh
```

---

### Container applications
``` bash
su alarm
sudo xbps-install -u docker docker-compose
sudo mkdir -p /etc/docker
vim /etc/docker/daemon.json
ln -s /etc/sv/containerd  /etc/runit/runsvdir/default/containerd
ln -s /etc/sv/docker /etc/runit/runsvdir/default/docker
sv status containerd
sv status docker
```

---

### Flatpak desktop applications
``` bash
su alarm
sudo xbps-install -u -y flatpak
flatpak remote-add --if-not-exists --user flathub https://dl.flathub.org/repo/flathub.flatpakrepo
flatpak remote-modify flathub --url=https://mirrors.ustc.edu.cn/flathub
flatpak remotes --show-details # show
flatpak list # show already install

# Install wechat
flatpak install -y com.tencent.WeChat
# Application file path： $HOME/.var/app/com.tencent.WeChat/xwechat_files

# Install wps-office
flatpak install -y com.wps.Office

# Install cloudmusic
flatpak install -y com.github.gmg137.netease-cloud-music-gtk
```

---

### Virtual environment install
``` bash
su root
# install tools
xbps-install -u -y libvirt virt-manager qemu bridge-utils dnsmasq
# run service
ln -s /etc/sv/libvirtd /etc/runit/runsvdir/default/libvirtd
ln -s /etc/sv/virtlogd /etc/runit/runsvdir/default/virtlogd
cp /data/git/DarkarchWM/app/virtual-conf/50-libvirt.rules /etc/polkit-1/rules.d
# switch user
su alarm
sudo usermod -a -G libvirt $USER
sudo usermod -a -G libvirt root
sudo usermod -a -G kvm $USER
sudo usermod -a -G kvm root
exit
# effective
sv restart libvirtd
sv restart virtlogd
```
#### Setup virtd network
``` bash
virsh net-destroy default # shutdown default network
virsh net-undefine default # delete default xml
cp /data/git/DarkarchWM/app/virtual-conf/10-vlan.xml /etc/libvirt/qemu/networks
# restart config
sudo virsh net-define /etc/libvirt/qemu/networks/10-vlan.xml
sudo virsh net-autostart vlan10
sudo virsh net-start vlan10
# show all networks
sudo virsh net-list --all
sudo virsh net-dumpxml vlan10 # check again
```
##### Show virtual host
``` bash
sudo virsh list # running
sudo virsh net-list # virtual network
sudo virsh net-dhcp-leases vlan10 # connected via DHCP under the virtual network
```
##### Option(Iso and drivers)
``` bash
# the system ISO files path: " /var/lib/libvirt/images "
# https://fedorapeople.org/groups/virt/virtio-win/direct-downloads/archive-virtio/
```
