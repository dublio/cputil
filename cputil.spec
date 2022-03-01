Name:           cputil
Version:        1.0
Release:        1%{?dist}
Summary:        Generate a workload cost specific cpu usage
License:        GPLv3
URL:            https://github.com/dublio/cputil
Source0:        https://github.com/dublio/cputil/releases/download/v%{version}/%{name}-%{version}.tar.gz
BuildRequires: gcc make
#Requires:


%description
This software can generate a workload that cost specific cpu usage.


%prep
%autosetup


%build
%{set_build_flags}
%{make_build}


%install
make mandir=$RPM_BUILD_ROOT/%{_mandir} bindir=$RPM_BUILD_ROOT/%{_bindir} install


%files
%doc README.md
%license LICENSE
%{_bindir}/cputil
%{_mandir}/man1/cputil.1*


%changelog
* Fri Mar 27 2020 Weiping Zhang <zwp10758@gmail.com> - 1.0-1
- First release cputil-1.0-1
