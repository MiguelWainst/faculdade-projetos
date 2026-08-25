import 'package:flutter/material.dart';

import '../models/ocorrencia_model.dart';
import 'filter_screen.dart';

class LogsScreen extends StatefulWidget {
  const LogsScreen({super.key});

  @override
  State<LogsScreen> createState() => _LogsScreenState();
}

class _LogsScreenState extends State<LogsScreen> {
  List<OcorrenciaModel> _todasOcorrencias = [];
  List<OcorrenciaModel> _ocorrencias = [];
  bool _carregando = true;

  @override
  void initState() {
    super.initState();
    _carregarOcorrencias();
  }

  Future<void> _carregarOcorrencias() async {
    await Future<void>.delayed(const Duration(seconds: 2));

    if (!mounted) return;
    setState(() {
      _todasOcorrencias = List.generate(50, _criarOcorrencia);
      _ocorrencias = List.of(_todasOcorrencias);
      _carregando = false;
    });
  }

  OcorrenciaModel _criarOcorrencia(int index) {
    const gravidades = Gravidade.values;
    final gravidade = gravidades[index % gravidades.length];
    final maquina = (index % 6) + 1;

    return OcorrenciaModel(
      id: index + 1,
      titulo: _tituloDaGravidade(gravidade),
      descricao: 'Máquina $maquina • Registro #${index + 1}',
      gravidade: gravidade,
      horario: DateTime.now().subtract(Duration(minutes: index * 4)),
    );
  }

  String _tituloDaGravidade(Gravidade gravidade) {
    return switch (gravidade) {
      Gravidade.critica => 'Falha crítica detectada',
      Gravidade.alerta => 'Parâmetro fora do ideal',
      Gravidade.info => 'Leitura registrada',
    };
  }

  String _labelDaGravidade(Gravidade gravidade) {
    return switch (gravidade) {
      Gravidade.critica => 'Crítico',
      Gravidade.alerta => 'Alerta',
      Gravidade.info => 'Info',
    };
  }

  IconData _iconeDaGravidade(Gravidade gravidade) {
    return switch (gravidade) {
      Gravidade.critica => Icons.error_outline,
      Gravidade.alerta => Icons.warning_amber_outlined,
      Gravidade.info => Icons.info_outline,
    };
  }

  Color _corDaGravidade(Gravidade gravidade, ColorScheme colors) {
    return switch (gravidade) {
      Gravidade.critica => colors.error,
      Gravidade.alerta => colors.tertiary,
      Gravidade.info => colors.primary,
    };
  }

  void _alternarReconhecimento(int index) {
    final ocorrencia = _ocorrencias[index];
    final atualizada = ocorrencia.copyWith(
      reconhecida: !ocorrencia.reconhecida,
    );

    setState(() {
      _ocorrencias[index] = atualizada;
      final indiceOriginal = _todasOcorrencias.indexWhere(
        (item) => item.id == ocorrencia.id,
      );
      _todasOcorrencias[indiceOriginal] = atualizada;
    });
  }

  Future<void> _abrirFiltro() async {
    final filtroSelecionado = await Navigator.push<Gravidade>(
      context,
      MaterialPageRoute(builder: (_) => const FilterScreen()),
    );

    if (!mounted || filtroSelecionado == null) return;

    setState(() {
      _ocorrencias = _todasOcorrencias
          .where((ocorrencia) => ocorrencia.gravidade == filtroSelecionado)
          .toList();
    });

    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(
        content: Text(
          'Exibindo apenas logs do tipo: ${_labelDaGravidade(filtroSelecionado)}',
        ),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    final colors = Theme.of(context).colorScheme;

    return Scaffold(
      appBar: AppBar(
        title: const Text('Logs de Ocorrência'),
        actions: [
          TextButton.icon(
            onPressed: _abrirFiltro,
            icon: const Icon(Icons.filter_alt_outlined),
            label: const Text('Filtrar'),
          ),
        ],
      ),
      body: _carregando
          ? const Center(child: CircularProgressIndicator())
          : ListView.builder(
              itemCount: _ocorrencias.length,
              itemBuilder: (context, index) {
                final ocorrencia = _ocorrencias[index];
                final cor = _corDaGravidade(ocorrencia.gravidade, colors);

                return ListTile(
                  leading: CircleAvatar(
                    backgroundColor: cor.withValues(alpha: 0.12),
                    foregroundColor: cor,
                    child: Icon(_iconeDaGravidade(ocorrencia.gravidade)),
                  ),
                  title: Text(ocorrencia.titulo),
                  subtitle: Text(
                    '${ocorrencia.descricao}\n${_labelDaGravidade(ocorrencia.gravidade)} • ${ocorrencia.horario.hour.toString().padLeft(2, '0')}:${ocorrencia.horario.minute.toString().padLeft(2, '0')}',
                  ),
                  isThreeLine: true,
                  trailing: IconButton(
                    tooltip: ocorrencia.reconhecida
                        ? 'Desfazer reconhecimento'
                        : 'Reconhecer alarme',
                    onPressed: () => _alternarReconhecimento(index),
                    icon: Icon(
                      ocorrencia.reconhecida
                          ? Icons.check_circle
                          : Icons.check_circle_outline,
                      color: ocorrencia.reconhecida ? colors.primary : null,
                    ),
                  ),
                );
              },
            ),
    );
  }
}
