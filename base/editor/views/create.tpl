<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Templates\View;
	use Base\Templates\HTML\Element\Form;

	class Create extends View {

		public function ToVar(Editor $editor, array $fields, array $data, string $title): string {
			$this->Start();
			$this->Render($editor, $fields, $data, $title);
			return $this->Read();
		}

		public function Render(Editor $editor, array $fields, array $data, string $title) {
			$form = new Form($data);
		?>
			<h1><?= $title; ?></h1>
			<?php
				$form->Begin($editor->do_create->GetPath());
				foreach ($fields as $name => $field) if ($field['skin'] == 'hidden') $form->Element('hidden', $name, $field['default'])
			?>
			<table class = "create">
				<tbody>
					<?php foreach ($fields as $name => $field) { if ($field['skin'] == 'hidden') continue; ?>
						<tr>
							<th><?= $field['name']; ?>:</th>
							<td><?php $form->Element($field['skin'], $name, $field['default'], $fields['params'] ?? []); ?></td>
						</tr>
					<?php } ?>
				</tbody>
			</table>
			<?php $form->Submit('Создать', $editor->do_create->GetClick()); $form->End(); ?>
		<?php }

	}