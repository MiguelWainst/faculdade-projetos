import 'package:flutter/material.dart';

import '../models/ocorrencia_model.dart';

class FilterScreen extends StatelessWidget {
  const FilterScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Filtrar por gravidade')),
      body: ListView(
        padding: const EdgeInsets.all(16),
        children: [
          Text(
            'Selecione a categoria desejada',
            style: Theme.of(context).textTheme.titleMedium,
          ),
          const SizedBox(height: 12),
          _FilterOption(
            gravidade: Gravidade.critica,
            label: 'Crítico',
            description: 'Falhas que exigem atenção imediata.',
            icon: Icons.error_outline,
          ),
          _FilterOption(
            gravidade: Gravidade.alerta,
            label: 'Alerta',
            description: 'Parâmetros que merecem acompanhamento.',
            icon: Icons.warning_amber_outlined,
          ),
          _FilterOption(
            gravidade: Gravidade.info,
            label: 'Info',
            description: 'Registros informativos de operação.',
            icon: Icons.info_outline,
          ),
        ],
      ),
    );
  }
}

class _FilterOption extends StatelessWidget {
  const _FilterOption({
    required this.gravidade,
    required this.label,
    required this.description,
    required this.icon,
  });

  final Gravidade gravidade;
  final String label;
  final String description;
  final IconData icon;

  @override
  Widget build(BuildContext context) {
    return Card(
      margin: const EdgeInsets.only(bottom: 12),
      child: ListTile(
        leading: Icon(icon),
        title: Text(label),
        subtitle: Text(description),
        trailing: const Icon(Icons.chevron_right),
        onTap: () => Navigator.pop(context, gravidade),
      ),
    );
  }
}
