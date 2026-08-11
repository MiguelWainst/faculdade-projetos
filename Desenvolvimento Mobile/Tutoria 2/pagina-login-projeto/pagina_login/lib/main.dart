import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class RegistrationData {
  const RegistrationData({
    required this.name,
    required this.email,
    required this.password,
  });

  final String name;
  final String email;
  final String password;
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Cadastro em 2 etapas',
      theme: ThemeData(
        useMaterial3: true,
        colorScheme: ColorScheme.fromSeed(
          seedColor: const Color(0xFF215A8C),
        ),
      ),
      home: const HomePage(),
    );
  }
}

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  RegistrationData? _lastRegistration;

  Future<void> _startRegistration() async {
    final result = await Navigator.of(context).push<RegistrationData>(
      MaterialPageRoute(
        builder: (context) => const RegistrationStepOnePage(),
      ),
    );

    if (!mounted || result == null) {
      return;
    }

    setState(() {
      _lastRegistration = result;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Cadastro em 2 etapas'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(24),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            const SizedBox(height: 16),
            Text(
              'Fluxo assíncrono com retorno de dados entre telas.',
              style: Theme.of(context).textTheme.headlineSmall,
            ),
            const SizedBox(height: 12),
            Text(
              'A primeira tela coleta nome e e-mail. A segunda recebe esses dados, pede a senha e devolve o cadastro completo por await.',
              style: Theme.of(context).textTheme.bodyMedium,
            ),
            const SizedBox(height: 24),
            FilledButton(
              onPressed: _startRegistration,
              child: const Text('Iniciar cadastro'),
            ),
            const SizedBox(height: 24),
            if (_lastRegistration != null)
              Card(
                child: Padding(
                  padding: const EdgeInsets.all(16),
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Text(
                        'Cadastro concluído',
                        style: Theme.of(context).textTheme.titleMedium,
                      ),
                      const SizedBox(height: 8),
                      Text('Nome: ${_lastRegistration!.name}'),
                      Text('E-mail: ${_lastRegistration!.email}'),
                      Text('Senha: ${'*' * _lastRegistration!.password.length}'),
                    ],
                  ),
                ),
              )
            else
              const Text('Nenhum cadastro finalizado ainda.'),
          ],
        ),
      ),
    );
  }
}

class RegistrationStepOnePage extends StatefulWidget {
  const RegistrationStepOnePage({super.key});

  @override
  State<RegistrationStepOnePage> createState() => _RegistrationStepOnePageState();
}

class _RegistrationStepOnePageState extends State<RegistrationStepOnePage> {
  final _formKey = GlobalKey<FormState>();
  final _nameController = TextEditingController();
  final _emailController = TextEditingController();

  @override
  void dispose() {
    _nameController.dispose();
    _emailController.dispose();
    super.dispose();
  }

  Future<void> _goToStepTwo() async {
    if (!_formKey.currentState!.validate()) {
      return;
    }

    final result = await Navigator.of(context).push<RegistrationData>(
      MaterialPageRoute(
        builder: (context) => RegistrationStepTwoPage(
          name: _nameController.text.trim(),
          email: _emailController.text.trim(),
        ),
      ),
    );

    if (!mounted || result == null) {
      return;
    }

    Navigator.of(context).pop(result);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Etapa 1 de 2')),
      body: SafeArea(
        child: Padding(
          padding: const EdgeInsets.all(24),
          child: Form(
            key: _formKey,
            child: ListView(
              children: [
                Text(
                  'Dados básicos',
                  style: Theme.of(context).textTheme.headlineSmall,
                ),
                const SizedBox(height: 20),
                TextFormField(
                  key: const ValueKey('name_field'),
                  controller: _nameController,
                  decoration: const InputDecoration(
                    labelText: 'Nome completo',
                    border: OutlineInputBorder(),
                  ),
                  validator: (value) {
                    if (value == null || value.trim().isEmpty) {
                      return 'Informe o nome';
                    }
                    return null;
                  },
                ),
                const SizedBox(height: 16),
                TextFormField(
                  key: const ValueKey('email_field'),
                  controller: _emailController,
                  keyboardType: TextInputType.emailAddress,
                  decoration: const InputDecoration(
                    labelText: 'E-mail',
                    border: OutlineInputBorder(),
                  ),
                  validator: (value) {
                    final text = value?.trim() ?? '';
                    if (text.isEmpty) {
                      return 'Informe o e-mail';
                    }
                    if (!text.contains('@')) {
                      return 'E-mail inválido';
                    }
                    return null;
                  },
                ),
                const SizedBox(height: 24),
                FilledButton(
                  onPressed: _goToStepTwo,
                  child: const Text('Continuar'),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}

class RegistrationStepTwoPage extends StatefulWidget {
  const RegistrationStepTwoPage({
    super.key,
    required this.name,
    required this.email,
  });

  final String name;
  final String email;

  @override
  State<RegistrationStepTwoPage> createState() => _RegistrationStepTwoPageState();
}

class _RegistrationStepTwoPageState extends State<RegistrationStepTwoPage> {
  final _formKey = GlobalKey<FormState>();
  final _passwordController = TextEditingController();
  final _confirmController = TextEditingController();

  @override
  void dispose() {
    _passwordController.dispose();
    _confirmController.dispose();
    super.dispose();
  }

  Future<void> _finishRegistration() async {
    if (!_formKey.currentState!.validate()) {
      return;
    }

    await Future<void>.delayed(const Duration(milliseconds: 250));

    if (!mounted) {
      return;
    }

    Navigator.of(context).pop(
      RegistrationData(
        name: widget.name,
        email: widget.email,
        password: _passwordController.text,
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Etapa 2 de 2')),
      body: SafeArea(
        child: Padding(
          padding: const EdgeInsets.all(24),
          child: Form(
            key: _formKey,
            child: ListView(
              children: [
                Text(
                  'Confirme os dados',
                  style: Theme.of(context).textTheme.headlineSmall,
                ),
                const SizedBox(height: 16),
                Card(
                  child: Padding(
                    padding: const EdgeInsets.all(16),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        Text('Nome: ${widget.name}'),
                        Text('E-mail: ${widget.email}'),
                      ],
                    ),
                  ),
                ),
                const SizedBox(height: 20),
                TextFormField(
                  key: const ValueKey('password_field'),
                  controller: _passwordController,
                  obscureText: true,
                  decoration: const InputDecoration(
                    labelText: 'Senha',
                    border: OutlineInputBorder(),
                  ),
                  validator: (value) {
                    if (value == null || value.length < 6) {
                      return 'Use ao menos 6 caracteres';
                    }
                    return null;
                  },
                ),
                const SizedBox(height: 16),
                TextFormField(
                  key: const ValueKey('confirm_password_field'),
                  controller: _confirmController,
                  obscureText: true,
                  decoration: const InputDecoration(
                    labelText: 'Confirmar senha',
                    border: OutlineInputBorder(),
                  ),
                  validator: (value) {
                    if (value != _passwordController.text) {
                      return 'As senhas não coincidem';
                    }
                    return null;
                  },
                ),
                const SizedBox(height: 24),
                FilledButton(
                  onPressed: _finishRegistration,
                  child: const Text('Concluir cadastro'),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
