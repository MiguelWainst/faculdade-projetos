import 'package:flutter/material.dart';

/// Destino temporário do login; será preenchido com os sensores na próxima etapa.
class DashboardScreen extends StatelessWidget {
  const DashboardScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Dashboard de Sensores')),
      body: const Center(child: Text('Carregando sensores...')),
    );
  }
}
