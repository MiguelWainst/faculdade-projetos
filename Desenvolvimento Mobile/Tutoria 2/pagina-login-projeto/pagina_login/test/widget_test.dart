import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';

import 'package:pagina_login/main.dart';

void main() {
  testWidgets('Completes the two-step registration flow', (
    WidgetTester tester,
  ) async {
    await tester.pumpWidget(const MyApp());

    await tester.tap(find.text('Iniciar cadastro'));
    await tester.pumpAndSettle();

    await tester.enterText(find.byKey(const ValueKey('name_field')), 'Ana Lima');
    await tester.enterText(
      find.byKey(const ValueKey('email_field')),
      'ana@example.com',
    );
    await tester.tap(find.text('Continuar'));
    await tester.pumpAndSettle();

    await tester.enterText(
      find.byKey(const ValueKey('password_field')),
      '123456',
    );
    await tester.enterText(
      find.byKey(const ValueKey('confirm_password_field')),
      '123456',
    );
    await tester.tap(find.text('Concluir cadastro'));
    await tester.pumpAndSettle();

    expect(find.text('Cadastro concluído'), findsOneWidget);
    expect(find.text('Nome: Ana Lima'), findsOneWidget);
    expect(find.text('E-mail: ana@example.com'), findsOneWidget);
  });
}
