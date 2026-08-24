import 'package:flutter/material.dart';

import 'themes/app_theme.dart';

void main() {
  runApp(const SupervisaoMaquinasApp());
}

class SupervisaoMaquinasApp extends StatelessWidget {
  const SupervisaoMaquinasApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Supervisão de Máquinas',
      debugShowCheckedModeBanner: false,
      theme: AppTheme.lightTheme,
      home: const Scaffold(body: Center(child: CircularProgressIndicator())),
    );
  }
}
