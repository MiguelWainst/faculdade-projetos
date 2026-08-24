import 'package:flutter/material.dart';

/// Histórico de ocorrências, que será implementado na próxima atividade.
class LogsScreen extends StatelessWidget {
  const LogsScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Logs de Ocorrência')),
      body: const Center(child: CircularProgressIndicator()),
    );
  }
}
