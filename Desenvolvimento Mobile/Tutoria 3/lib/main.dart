import 'package:flutter/material.dart';

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
      home: const ListaOtimizadaScreen(),
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
              leading: const Icon(
                Icons.history_toggle_off,
                color: Colors.red,
              ),
              title: Text('Registro de Máquina #$numeroRegistro'),
              subtitle: const Text('Status: Sincronizado na Memória'),
            ),
          );
        },
      ),
    );
  }
}
