# BlackboxOS Architecture Design Document

## Overview
BlackboxOS is a Linux-based OS with a minimal kernel, Wayland compositor, and sandboxed app ecosystem. It prioritizes speed, security, and modularity.

## Kernel Choice
- **Chosen**: Minimal Linux kernel (5.15+ LTS) with targeted patches for low-latency scheduling (e.g., PREEMPT_RT).
- **Rationale**: Broad hardware support, mature ecosystem. Microkernel (e.g., seL4) rejected due to maintenance burden and limited driver support.
- **Config Options**:
  - CONFIG_PREEMPT=y for responsiveness.
  - CONFIG_ZRAM=y for memory compression.
  - CONFIG_SECURITY_APPARMOR=y for sandboxing.
  - CONFIG_SECURITY_SECCOMP=y for syscall filtering.
  - Trade-off: Larger kernel size vs. performance gains.

## Init & Services
- **Chosen**: systemd with minimal units, lazy-loading enabled.
- **Rationale**: Proven reliability, socket activation for services. Custom init considered but systemd's ecosystem wins.
- **Optimizations**: Disable unnecessary services; use socket-based activation.

## Display Server
- **Chosen**: Custom Wayland compositor based on wlroots, optimized for <16ms latency.
- **Rationale**: Modern, secure. X11 rejected for legacy issues.
- **Features**: Tiling WM, gesture support, low CPU usage.

## Filesystem & Storage
- **Chosen**: Btrfs with snapshots.
- **Rationale**: Fast, built-in rollback. Ext4 considered but lacks snapshots.
- **Trade-off**: Slight overhead vs. reliability.

## Package Management
- **Chosen**: OSTree + Flatpak.
- **Rationale**: Atomic updates, sandboxing. Custom manager rejected for complexity.
- **Features**: Rollbacks, secure repos.

## Sandboxing & Security
- Mandatory Flatpak-like containers, AppArmor profiles, secure boot.
- Privacy levels: Strict (no network), Balanced, Open.

## UX/UI
- Global search: FZF-like launcher.
- Modes: Simple (floating), Power (tiling).
- Animations: Skippable, minimal.

## Distinctive Features
1. AI search: Local ML model for suggestions.
2. Focus Mode: Pause background tasks.
3. Developer SDK: Rust-based templates.

## Performance Targets
- Boot: <5s SSD, <15s eMMC.
- App launch: <400ms cold.
- RAM: <600MB idle.

## Build & CI
- Reproducible with Nix or Docker.
- CI: GitHub Actions for builds, tests.

## Assumptions
- x86_64 primary, ARM64 secondary.
- No cloud dependencies for core features.
