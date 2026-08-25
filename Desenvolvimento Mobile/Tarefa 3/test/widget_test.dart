import 'package:flutter_test/flutter_test.dart';

import 'package:supervisao_maquinas/main.dart';

void main() {
  testWidgets('exibe o portal de acesso', (WidgetTester tester) async {
    await tester.pumpWidget(const SupervisaoMaquinasApp());

    expect(find.text('Portal de Acesso'), findsOneWidget);
    expect(find.text('Acessar painel'), findsOneWidget);
  });
}
