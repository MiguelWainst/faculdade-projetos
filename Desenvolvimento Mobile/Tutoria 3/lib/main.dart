import 'dart:async';

import 'package:flutter/material.dart';

import 'models/sensor_model.dart';

void main() {
  runApp(const TutoriaTresApp());
}

class TutoriaTresApp extends StatelessWidget {
  const TutoriaTresApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Tutoria 3 - Listas',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.red),
        useMaterial3: true,
      ),
      home: const ExerciciosScreen(),
    );
  }
}

class ExerciciosScreen extends StatelessWidget {
  const ExerciciosScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Tutoria 3 - Listas')),
      body: ListView(
        padding: const EdgeInsets.all(16),
        children: [
          _ExerciseTile(
            number: 1,
            title: 'O Otimizador de Listas',
            subtitle: 'Lista de logs renderizada com ListView.builder.',
            onTap: () => Navigator.of(context).push(
              MaterialPageRoute<void>(
                builder: (context) => const ListaOtimizadaScreen(),
              ),
            ),
          ),
          const SizedBox(height: 12),
          _ExerciseTile(
            number: 2,
            title: 'O Dashboard em Grade',
            subtitle: 'Sensores industriais em uma grade responsiva.',
            onTap: () => Navigator.of(context).push(
              MaterialPageRoute<void>(
                builder: (context) => const DashboardGridScreen(),
              ),
            ),
          ),
          const SizedBox(height: 12),
          _ExerciseTile(
            number: 3,
            title: 'O Guardião de Memória',
            subtitle: 'Monitor térmico que libera o Timer no dispose().',
            onTap: () => Navigator.of(context).push(
              MaterialPageRoute<void>(
                builder: (context) => const MonitorTermicoScreen(),
              ),
            ),
          ),
        ],
      ),
    );
  }
}

class _ExerciseTile extends StatelessWidget {
  const _ExerciseTile({
    required this.number,
    required this.title,
    required this.subtitle,
    required this.onTap,
  });

  final int number;
  final String title;
  final String subtitle;
  final VoidCallback onTap;

  @override
  Widget build(BuildContext context) {
    return Card(
      clipBehavior: Clip.antiAlias,
      child: ListTile(
        leading: CircleAvatar(child: Text('$number')),
        title: Text(title),
        subtitle: Text(subtitle),
        trailing: const Icon(Icons.chevron_right),
        onTap: onTap,
      ),
    );
  }
}

class ListaOtimizadaScreen extends StatelessWidget {
  const ListaOtimizadaScreen({super.key});

  static const _totalRegistros = 100;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Logs Industriais - Otimizado'),
        backgroundColor: Colors.red,
        foregroundColor: Colors.white,
      ),
      body: ListView.builder(
        padding: const EdgeInsets.symmetric(vertical: 8),
        itemCount: _totalRegistros,
        itemBuilder: (context, index) {
          final numeroRegistro = index + 1;

          return Card(
            margin: const EdgeInsets.symmetric(horizontal: 16, vertical: 4),
            child: ListTile(
              leading: const Icon(Icons.history_toggle_off, color: Colors.red),
              title: Text('Registro de Máquina #$numeroRegistro'),
              subtitle: const Text('Status: Sincronizado na Memória'),
            ),
          );
        },
      ),
    );
  }
}

class DashboardGridScreen extends StatelessWidget {
  const DashboardGridScreen({super.key});

  static const _sensores = [
    SensorModel(
      nome: 'Temperatura Motor A (WEG)',
      valor: '74.5 °C',
      statusAtivo: true,
    ),
    SensorModel(
      nome: 'Pressão Caldeira 02',
      valor: '12.4 Bar',
      statusAtivo: true,
    ),
    SensorModel(
      nome: 'Vibração Tear Malwee',
      valor: '0.2 mm/s',
      statusAtivo: false,
    ),
    SensorModel(
      nome: 'Consumo KWh Painel 3',
      valor: '450 KWh',
      statusAtivo: true,
    ),
    SensorModel(
      nome: 'Fluxo Entrada Hidráulica',
      valor: '15 L/min',
      statusAtivo: true,
    ),
    SensorModel(
      nome: 'Nível Solução Química',
      valor: '15%',
      statusAtivo: false,
    ),
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Telemetria Industrial - Sensores'),
        backgroundColor: Colors.blue,
        foregroundColor: Colors.white,
      ),
      body: Padding(
        padding: const EdgeInsets.all(12),
        child: GridView.builder(
          itemCount: _sensores.length,
          gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
            crossAxisCount: 2,
            crossAxisSpacing: 12,
            mainAxisSpacing: 12,
            childAspectRatio: 1.1,
          ),
          itemBuilder: (context, index) {
            return SensorCard(sensor: _sensores[index]);
          },
        ),
      ),
    );
  }
}

class SensorCard extends StatelessWidget {
  const SensorCard({super.key, required this.sensor});

  final SensorModel sensor;

  @override
  Widget build(BuildContext context) {
    final statusColor = sensor.statusAtivo ? Colors.green : Colors.red;
    final statusLabel = sensor.statusAtivo ? 'Ativo' : 'Inativo';

    return Card(
      elevation: 4,
      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(12)),
      child: Padding(
        padding: const EdgeInsets.all(12),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                const Icon(Icons.sensors, color: Colors.blue),
                Row(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Container(
                      width: 12,
                      height: 12,
                      decoration: BoxDecoration(
                        color: statusColor,
                        shape: BoxShape.circle,
                      ),
                    ),
                    const SizedBox(width: 4),
                    Text(statusLabel, style: const TextStyle(fontSize: 11)),
                  ],
                ),
              ],
            ),
            const Spacer(),
            Text(
              sensor.nome,
              maxLines: 2,
              overflow: TextOverflow.ellipsis,
              style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 13),
            ),
            const SizedBox(height: 4),
            Text(
              sensor.valor,
              style: const TextStyle(
                fontSize: 18,
                fontWeight: FontWeight.w900,
                color: Colors.blue,
              ),
            ),
          ],
        ),
      ),
    );
  }
}

class MonitorTermicoScreen extends StatefulWidget {
  const MonitorTermicoScreen({super.key});

  @override
  State<MonitorTermicoScreen> createState() => _MonitorTermicoScreenState();
}

class _MonitorTermicoScreenState extends State<MonitorTermicoScreen> {
  Timer? _timerTelemetria;
  double _temperaturaWEG = 45.0;

  @override
  void initState() {
    super.initState();
    _timerTelemetria = Timer.periodic(const Duration(seconds: 1), (timer) {
      setState(() {
        _temperaturaWEG = 45.0 + (timer.tick % 5) * 0.4;
      });
      debugPrint(
        '[SISTEMA ATIVO] Monitorando temperatura em tempo real: '
        '$_temperaturaWEG °C',
      );
    });
  }

  @override
  void dispose() {
    _timerTelemetria?.cancel();
    debugPrint(
      '[HIGIENE DE MEMÓRIA] Timer de telemetria destruído. Recursos liberados.',
    );
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Monitor Térmico'),
        backgroundColor: Colors.blue,
        foregroundColor: Colors.white,
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Icon(Icons.thermostat, size: 80, color: Colors.orange),
            const SizedBox(height: 16),
            const Text(
              'Sensor Motor Principal (WEG)',
              style: TextStyle(fontSize: 18, color: Colors.grey),
            ),
            const SizedBox(height: 8),
            Text(
              '${_temperaturaWEG.toStringAsFixed(1)} °C',
              style: const TextStyle(fontSize: 48, fontWeight: FontWeight.bold),
            ),
            const SizedBox(height: 24),
            const Padding(
              padding: EdgeInsets.symmetric(horizontal: 32),
              child: Text(
                'Abra o console e volte para a tela anterior. Os logs cessam '
                'quando dispose() cancela o Timer, comprovando a liberação do recurso.',
                textAlign: TextAlign.center,
                style: TextStyle(
                  fontSize: 12,
                  fontStyle: FontStyle.italic,
                  color: Colors.grey,
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
