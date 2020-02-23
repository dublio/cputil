Name:           cputil
Version:        1.0
Release:        1%{?dist}
Summary:        Generate a workload cost specific cpu usage
License:        GPLv3
URL:            https://github.com/dublio/cputil
Source0:        https://github.com/dublio/cputil/releases/download/1.0/cputil-1.0.tar.gz
#BuildRequires:
#Requires:

# disable producing debuginfo for this package
%global debug_package %{nil}

%global dirfull %{name}-%{version}

%description
This software can generate a workload that cost specific cpu usage.


%prep
%autosetup -n %{dirfull}


%build
make %{?_smp_flags}


%install
install -d %{buildroot}/%{_bindir}
install %{_builddir}/%{dirfull}/cputil %{buildroot}/%{_bindir}

install -d %{buildroot}/%{_mandir}/man1
install -m 0644 %{_builddir}/%{dirfull}/cputil.1 %{buildroot}/%{_mandir}/man1


%files
%{_bindir}/cputil
# node that: man page will be compress as .gz file
%{_mandir}/man1/cputil.1.gz


%changelog
* Sun Feb 23 2020 Weiping Zhang <zwp10758@gmail.com>
- Release v1.0.
