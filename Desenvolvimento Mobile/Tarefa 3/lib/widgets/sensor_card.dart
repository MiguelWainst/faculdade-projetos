import 'package:flutter/material.dart';

import '../models/sensor_model.dart';

class SensorCard extends StatelessWidget {
  const SensorCard({required this.sensor, super.key});

  final SensorModel sensor;

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    final status = _statusVisual(theme.colorScheme);

    return Card(
      child: Padding(
        padding: const EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Icon(status.icon, color: status.color),
            const Spacer(),
            Text(sensor.nome, style: theme.textTheme.titleMedium),
            const SizedBox(height: 4),
            Text(
              '${sensor.valor.toStringAsFixed(sensor.valor % 1 == 0 ? 0 : 1)} ${sensor.unidade}',
              style: theme.textTheme.headlineSmall,
            ),
            const SizedBox(height: 8),
            Text(status.label,
                style:
                    theme.textTheme.labelLarge?.copyWith(color: status.color)),
          ],
        ),
      ),
    );
  }

  _SensorStatusVisual _statusVisual(ColorScheme colors) {
    return switch (sensor.status) {
      SensorStatus.normal => _SensorStatusVisual(
          label: 'Normal',
          icon: Icons.check_circle_outline,
          color: colors.primary,
        ),
      SensorStatus.alerta => _SensorStatusVisual(
          label: 'Alerta',
          icon: Icons.warning_amber_outlined,
          color: colors.tertiary,
        ),
      SensorStatus.critico => _SensorStatusVisual(
          label: 'Crítico',
          icon: Icons.error_outline,
          color: colors.error,
        ),
    };
  }
}

class _SensorStatusVisual {
  const _SensorStatusVisual({
    required this.label,
    required this.icon,
    required this.color,
  });

  final String label;
  final IconData icon;
  final Color color;
}
