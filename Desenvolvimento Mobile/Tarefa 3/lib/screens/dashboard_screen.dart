import 'package:flutter/material.dart';

import '../models/sensor_model.dart';
import '../widgets/app_action_button.dart';
import '../widgets/sensor_card.dart';
import 'logs_screen.dart';

class DashboardScreen extends StatelessWidget {
  const DashboardScreen({super.key});

  static const _sensores = [
    SensorModel(
      nome: 'Temperatura',
      valor: 72.4,
      unidade: '°C',
      status: SensorStatus.alerta,
    ),
    SensorModel(
      nome: 'Pressão',
      valor: 5.8,
      unidade: 'bar',
      status: SensorStatus.normal,
    ),
    SensorModel(
      nome: 'Vibração',
      valor: 2.1,
      unidade: 'mm/s',
      status: SensorStatus.normal,
    ),
    SensorModel(
      nome: 'Rotação',
      valor: 1480,
      unidade: 'RPM',
      status: SensorStatus.normal,
    ),
    SensorModel(
      nome: 'Nível de óleo',
      valor: 18,
      unidade: '%',
      status: SensorStatus.critico,
    ),
    SensorModel(
      nome: 'Umidade',
      valor: 46,
      unidade: '%',
      status: SensorStatus.normal,
    ),
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Dashboard de Sensores'),
        actions: [
          IconButton(
            tooltip: 'Logs de ocorrência',
            onPressed: () {
              Navigator.push(
                context,
                MaterialPageRoute(builder: (_) => const LogsScreen()),
              );
            },
            icon: const Icon(Icons.receipt_long_outlined),
          ),
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            Text('Visão geral',
                style: Theme.of(context).textTheme.headlineSmall),
            const SizedBox(height: 4),
            Text(
              'Leituras atualizadas dos equipamentos em operação.',
              style: Theme.of(context).textTheme.bodyMedium,
            ),
            const SizedBox(height: 20),
            Expanded(
              child: GridView.builder(
                itemCount: _sensores.length,
                gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                  crossAxisCount: 2,
                  mainAxisSpacing: 12,
                  crossAxisSpacing: 12,
                  childAspectRatio: 1.05,
                ),
                itemBuilder: (context, index) {
                  return SensorCard(sensor: _sensores[index]);
                },
              ),
            ),
            const SizedBox(height: 16),
            AppActionButton(
              label: 'Ver logs de ocorrência',
              icon: Icons.receipt_long_outlined,
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (_) => const LogsScreen()),
                );
              },
            ),
          ],
        ),
      ),
    );
  }
}
