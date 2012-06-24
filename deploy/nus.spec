%define distver 10
%define disttag suse

Name:      nus
Summary:   Nemesis Utilities System is a cross-plataform C++ framework 
Version:   0.2
Release:   0.%{disttag}%{distver}
License:   LGPL
Vendor:    Nemesis Project <angusyoung@gmail.com>
Group:     System/Libraries
BuildRoot: /var/tmp/install
BuildRequires: libxml2, openssl, libstdc++

%description
NUS - Nemesis Utilities System - is a cross-platform C++ application development framework which focus on the development of network applications, non-gui applications, cgi scripts, database applications and any kind of application that needs interoperability. NUS is very modular and its functionality is separated in modules, as such making it easy to maintain, debug and deploy. The NUS Library was greatly inspired in other libraries I have been working on the latest years like, for example, Trolltech's QT .

For the most up-to-date information and sources, visit http://dev.angusyoung.org

%files
%defattr(-,root,root)
/usr

%changelog
* Wed Apr 18 2007 - angusyoung (at) gmail.com
- Initial release
