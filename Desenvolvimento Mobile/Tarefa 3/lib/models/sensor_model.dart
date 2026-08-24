class SensorModel {
  const SensorModel({
    required this.nome,
    required this.valor,
    required this.unidade,
    required this.status,
  });

  final String nome;
  final double valor;
  final String unidade;
  final SensorStatus status;
}

enum SensorStatus { normal, alerta, critico }
