import 'package:flutter/material.dart';

/// Botão de ação principal reutilizado nas telas da aplicação.
class AppActionButton extends StatelessWidget {
  const AppActionButton({
    required this.label,
    required this.onPressed,
    this.icon,
    super.key,
  });

  final String label;
  final VoidCallback onPressed;
  final IconData? icon;

  @override
  Widget build(BuildContext context) {
    return ElevatedButton.icon(
      onPressed: onPressed,
      icon: icon == null ? const SizedBox.shrink() : Icon(icon),
      label: Text(label),
    );
  }
}
