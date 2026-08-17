import 'package:flutter/material.dart';

void main() {
  runApp(const CatalogoIndustrialApp());
}

// ==========================================
// MODELO DE DADOS (Orientação a Objetos)
// ==========================================
class Produto {
  final String id;
  final String nome;
  final String descricao;
  final double preco;
  final IconData icone;

  Produto({
    required this.id,
    required this.nome,
    required this.descricao,
    required this.preco,
    required this.icone,
  });

  // Método para formatar o preço visualmente
  String get precoFormatado => 'R\$ ${preco.toStringAsFixed(2).replaceAll('.', ',')}';
}

// ==========================================
// APLICATIVO E TEMA PRINCIPAL
// ==========================================
class CatalogoIndustrialApp extends StatelessWidget {
  const CatalogoIndustrialApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Catálogo Industrial JS',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        useMaterial3: true, // Ativa o design moderno do Flutter
        colorScheme: ColorScheme.fromSeed(
          seedColor: const Color(0xFF00579D),
          primary: const Color(0xFF00579D),
        ),
        appBarTheme: const AppBarTheme(
          backgroundColor: Color(0xFF00579D),
          foregroundColor: Colors.white,
          centerTitle: true,
        ),
      ),
      home: HomeScreen(),
    );
  }
}

// ==========================================
// TELA 1: HOME (Lista de Produtos)
// ==========================================
class HomeScreen extends StatelessWidget {
  HomeScreen({super.key});

  // Lista de produtos agora como objetos reais
  final List<Produto> produtos = [
    Produto(
      id: 'p1',
      nome: 'Motor Elétrico W22',
      descricao: 'Alta eficiência para uso industrial contínuo. Carcaça em ferro fundido, ideal para as aplicações mais severas.',
      preco: 1250.00,
      icone: Icons.precision_manufacturing,
    ),
    Produto(
      id: 'p2',
      nome: 'Inversor CFW300',
      descricao: 'Controle preciso de velocidade para maquinário. Design compacto e facilidade de parametrização.',
      preco: 850.00,
      icone: Icons.memory,
    ),
    Produto(
      id: 'p3',
      nome: 'Contator Tripolar CWB',
      descricao: 'Solução compacta para manobra de motores. Contatos de alta durabilidade e montagem em trilho DIN.',
      preco: 120.00,
      icone: Icons.electrical_services,
    ),
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Equipamentos e Motores', style: TextStyle(fontWeight: FontWeight.bold)),
      ),
      body: Column(
        children: [
          Container(
            width: double.infinity,
            padding: const EdgeInsets.symmetric(vertical: 12, horizontal: 16),
            color: Theme.of(context).colorScheme.primaryContainer,
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Icon(Icons.location_on, color: Theme.of(context).colorScheme.primary, size: 20),
                const SizedBox(width: 8),
                Text(
                  'Polo Industrial - Jaraguá do Sul',
                  style: TextStyle(
                    fontSize: 14,
                    fontWeight: FontWeight.bold,
                    color: Theme.of(context).colorScheme.primary,
                  ),
                ),
              ],
            ),
          ),
          Expanded(
            child: ListView.builder(
              itemCount: produtos.length,
              itemBuilder: (context, index) {
                final produto = produtos[index];
                
                return GestureDetector(
                  onTap: () {
                    // Navegação empilhada
                    Navigator.push(
                      context,
                      MaterialPageRoute(
                        builder: (context) => DetailsScreen(produto: produto),
                      ),
                    );
                  },
                  child: Container(
                    margin: const EdgeInsets.only(left: 16, right: 16, top: 12),
                    padding: const EdgeInsets.all(12),
                    decoration: BoxDecoration(
                      color: Colors.white,
                      borderRadius: BorderRadius.circular(12),
                      border: Border.all(color: Colors.grey.shade200),
                      boxShadow: [
                        BoxShadow(
                          color: Colors.black.withOpacity(0.05),
                          blurRadius: 8,
                          offset: const Offset(0, 4),
                        ),
                      ],
                    ),
                    child: Row(
                      children: [
                        // O Hero cria uma animação visual do ícone até a próxima tela
                        Hero(
                          tag: produto.id,
                          child: Container(
                            width: 70,
                            height: 70,
                            decoration: BoxDecoration(
                              color: Theme.of(context).colorScheme.primary.withOpacity(0.1),
                              borderRadius: BorderRadius.circular(8),
                            ),
                            child: Icon(produto.icone, color: Theme.of(context).colorScheme.primary, size: 36),
                          ),
                        ),
                        const SizedBox(width: 16),
                        Expanded(
                          child: Column(
                            crossAxisAlignment: CrossAxisAlignment.start,
                            children: [
                              Text(
                                produto.nome,
                                style: const TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
                              ),
                              const SizedBox(height: 6),
                              Text(
                                produto.precoFormatado,
                                style: const TextStyle(fontSize: 16, color: Colors.green, fontWeight: FontWeight.w600),
                              ),
                            ],
                          ),
                        ),
                        Icon(Icons.chevron_right, color: Colors.grey.shade400),
                      ],
                    ),
                  ),
                );
              },
            ),
          ),
        ],
      ),
    );
  }
}

// ==========================================
// TELA 2: DETALHES (StatefulWidget)
// ==========================================
class DetailsScreen extends StatefulWidget {
  final Produto produto; // Recebe o objeto da classe Produto

  const DetailsScreen({super.key, required this.produto});

  @override
  State<DetailsScreen> createState() => _DetailsScreenState();
}

class _DetailsScreenState extends State<DetailsScreen> {
  // Estado local para controle de quantidade
  int quantidade = 1;

  void _incrementar() {
    setState(() => quantidade++);
  }

  void _decrementar() {
    if (quantidade > 1) {
      setState(() => quantidade--);
    }
  }

  @override
  Widget build(BuildContext context) {
    // Calculando o total dinamicamente
    final double valorTotal = widget.produto.preco * quantidade;
    final String totalFormatado = 'R\$ ${valorTotal.toStringAsFixed(2).replaceAll('.', ',')}';

    return Scaffold(
      appBar: AppBar(
        title: const Text('Detalhes do Item', style: TextStyle(fontSize: 18)),
      ),
      body: Column(
        children: [
          Expanded(
            child: SingleChildScrollView(
              padding: const EdgeInsets.all(20.0),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Center(
                    child: Hero(
                      tag: widget.produto.id,
                      child: Container(
                        width: double.infinity,
                        height: 180,
                        decoration: BoxDecoration(
                          color: Theme.of(context).colorScheme.primary.withOpacity(0.05),
                          borderRadius: BorderRadius.circular(16),
                          border: Border.all(color: Theme.of(context).colorScheme.primary.withOpacity(0.2)),
                        ),
                        child: Icon(widget.produto.icone, size: 80, color: Theme.of(context).colorScheme.primary),
                      ),
                    ),
                  ),
                  const SizedBox(height: 24),
                  Text(
                    widget.produto.nome,
                    style: const TextStyle(fontSize: 26, fontWeight: FontWeight.bold),
                  ),
                  const SizedBox(height: 8),
                  Text(
                    widget.produto.precoFormatado,
                    style: const TextStyle(fontSize: 22, color: Colors.green, fontWeight: FontWeight.bold),
                  ),
                  const SizedBox(height: 24),
                  const Text(
                    'Descrição Técnica',
                    style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
                  ),
                  const SizedBox(height: 8),
                  Text(
                    widget.produto.descricao,
                    style: const TextStyle(fontSize: 16, color: Colors.black87, height: 1.5),
                  ),
                  const SizedBox(height: 32),
                  
                  // Bloco de Controle de Quantidade
                  Container(
                    padding: const EdgeInsets.all(16),
                    decoration: BoxDecoration(
                      color: Colors.grey.shade100,
                      borderRadius: BorderRadius.circular(12),
                      border: Border.all(color: Colors.grey.shade300),
                    ),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceBetween,
                      children: [
                        const Text(
                          'Quantidade',
                          style: TextStyle(fontSize: 16, fontWeight: FontWeight.bold),
                        ),
                        Row(
                          children: [
                            IconButton(
                              onPressed: _decrementar,
                              icon: const Icon(Icons.remove_circle),
                              color: quantidade > 1 ? Colors.red : Colors.grey.shade400,
                              iconSize: 32,
                            ),
                            Container(
                              padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 8),
                              child: Text(
                                '$quantidade',
                                style: const TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
                              ),
                            ),
                            IconButton(
                              onPressed: _incrementar,
                              icon: const Icon(Icons.add_circle),
                              color: Theme.of(context).colorScheme.primary,
                              iconSize: 32,
                            ),
                          ],
                        )
                      ],
                    ),
                  ),
                ],
              ),
            ),
          ),
          
          // Rodapé fixo com o Botão e Total
          Container(
            padding: const EdgeInsets.all(20),
            decoration: BoxDecoration(
              color: Colors.white,
              boxShadow: [
                BoxShadow(color: Colors.black.withOpacity(0.05), blurRadius: 10, offset: const Offset(0, -5)),
              ],
            ),
            child: SafeArea(
              child: Row(
                children: [
                  Expanded(
                    flex: 2,
                    child: Column(
                      mainAxisSize: MainAxisSize.min,
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        const Text('Total:', style: TextStyle(color: Colors.grey, fontSize: 14)),
                        Text(
                          totalFormatado,
                          style: const TextStyle(fontWeight: FontWeight.bold, fontSize: 20, color: Colors.green),
                        ),
                      ],
                    ),
                  ),
                  Expanded(
                    flex: 3,
                    child: SizedBox(
                      height: 50,
                      child: ElevatedButton(
                        style: ElevatedButton.styleFrom(
                          backgroundColor: Theme.of(context).colorScheme.primary,
                          foregroundColor: Colors.white,
                          shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(8)),
                        ),
                        onPressed: () {
                          ScaffoldMessenger.of(context).showSnackBar(
                            SnackBar(
                              backgroundColor: Colors.green.shade800,
                              content: Text('✅ $quantidade x ${widget.produto.nome} adicionado ao carrinho!'),
                              behavior: SnackBarBehavior.floating,
                            ),
                          );
                        },
                        child: const Text('ADICIONAR', style: TextStyle(fontSize: 16, fontWeight: FontWeight.bold)),
                      ),
                    ),
                  ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}