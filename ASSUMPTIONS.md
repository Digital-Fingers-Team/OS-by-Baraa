# Assumptions for BlackboxOS

## General
- Target OS is Linux-based for broad hardware support; microkernel rejected due to driver complexity.
- Builds run on Ubuntu 22.04 (Focal compatible) with apt for dependencies.
- No proprietary tools; all open-source.
- x86_64 primary; ARM64 secondary (not built here).
- VM images use QEMU; ISO bootable in QEMU.
- Network downloads validated with SHA256 checksums.

## Compatibility
- Hardware: Assumes 2GB RAM for benchmarks; lower spec may degrade performance.
- Boot time: <=20s on QEMU with 2GB RAM; real hardware may vary.
- App launch: <=800ms cold start on CI VM; depends on CPU.

## Security
- Sandboxing uses AppArmor; tests assume kernel support.
- Full disk encryption via LUKS in installer.

## Build
- Scripts idempotent; require internet for downloads.
- CI produces artifacts; local builds may need manual tweaks.

## Future
- AI features local-only; no cloud.
- Migration tools stubbed; full impl later.
