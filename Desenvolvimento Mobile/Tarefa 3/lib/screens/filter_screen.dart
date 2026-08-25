import 'package:flutter/material.dart';

/// Escolha de gravidade; as opções e o retorno serão concluídos na próxima etapa.
class FilterScreen extends StatelessWidget {
  const FilterScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Filtrar por gravidade')),
      body: const Center(child: Text('Selecione uma categoria de gravidade.')),
    );
  }
}
