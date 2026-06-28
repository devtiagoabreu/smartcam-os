# Contributing to SmartCam Platform

Thank you for considering contributing to the SmartCam Platform.

## Code of Conduct

By participating, you agree to uphold the [Code of Conduct](CODE_OF_CONDUCT.md).

## How to Contribute

1. Fork the repository
2. Create a feature branch from `develop`
3. Write code following the [Coding Standard](docs/17-coding-standard.md)
4. Write tests following the [Test Plan](docs/18-test-plan.md)
5. Submit a pull request

## Pull Request Checklist

- [ ] Code follows Coding Standard
- [ ] Doxygen comments added for public APIs
- [ ] No `delay()` usage (use non-blocking timers)
- [ ] No `Serial.println()` (use Logger Service)
- [ ] No hardcoded GPIOs (use Configuration Manager)
- [ ] Error handling uses `Result` type
- [ ] CHANGELOG updated
- [ ] Documentation updated if API changed

## Branch Naming

- `feature/short-description` for new features
- `bugfix/short-description` for bug fixes
- `release/vX.Y.Z` for release branches

## Git Flow

Feature branches branch from `develop` and merge back via PR.
Release branches are created from `develop` when feature-complete.
Only `main` receives release tags.
