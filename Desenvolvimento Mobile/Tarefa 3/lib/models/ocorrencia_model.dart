class OcorrenciaModel {
  const OcorrenciaModel({
    required this.id,
    required this.titulo,
    required this.descricao,
    required this.gravidade,
    required this.horario,
    this.reconhecida = false,
  });

  final int id;
  final String titulo;
  final String descricao;
  final Gravidade gravidade;
  final DateTime horario;
  final bool reconhecida;

  OcorrenciaModel copyWith({bool? reconhecida}) {
    return OcorrenciaModel(
      id: id,
      titulo: titulo,
      descricao: descricao,
      gravidade: gravidade,
      horario: horario,
      reconhecida: reconhecida ?? this.reconhecida,
    );
  }
}

enum Gravidade { critica, alerta, info }
