<?php

	namespace Base\Templates\Editor;

	use Base\Editor;
	use Base\Templates\View;
	use Base\Templates\HTML\Element\Form;
	use Base\Templates\HTML\Element\Text;

	class Update extends View {

		public function ToVar(Editor $editor, int $id, array $fields, array $data, string $title): string {
			$this->Start();
			$this->Render($editor, $id, $fields, $data, $title);
			return $this->Read();
		}

		public function Render(Editor $editor, int $id, array $fields, array $data, string $title) {
			$form = new Form($data);
		?>
			<h1><?= $title; ?></h1>
		<?php
			$form->Begin($editor->do_create->GetPath());
			Text::object()->Render('id', $id, ['type' => 'hidden']);
			foreach ($fields as $name => $field) if ($field['skin'] == 'hidden') $form->Element('hidden', $name, $field['value'])
		?>
			<table class = "update">
				<tbody>
				<?php foreach ($fields as $name => $field) { if ($field['skin'] == 'hidden') continue; ?>
					<tr>
						<th><?= $field['name']; ?>:</th>
						<td><?php $form->Element($field['skin'], $name, $field['value'], $fields['params'] ?? []); ?></td>
					</tr>
				<?php } ?>
				</tbody>
			</table>
			<?php $form->Submit(); $form->End(); ?>
		<?php }

	}