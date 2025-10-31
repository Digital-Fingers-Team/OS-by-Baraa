# Design Choices

## Kernel
- Linux 5.15 with PREEMPT for low latency.
- Rationale: Broad support, performance.

## Compositor
- Wlroots-based minimal compositor.
- Rationale: Modern, fast.

## Filesystem
- Btrfs for snapshots.
- Rationale: Rollback support.

## Package Manager
- Flatpak for sandboxing.
- Rationale: Security, atomic updates.
