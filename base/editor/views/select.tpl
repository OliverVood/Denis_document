<?php

	namespace Base\Templates\Editor;

	use Base\Editor;
	use Base\Templates\View;

	class Select extends View {

		public function ToVar(Editor $editor, array $fields, array $items, string $title): string {
			$this->Start();
			$this->Render($editor, $fields, $items, $title);
			return $this->Read();
		}

		public function Render(Editor $editor, array $fields, array $items, string $title) { ?>
			<h1><?= $title; ?></h1>
			<table class = "select">
				<thead>
					<tr>
						<?php foreach ($fields as $field) { ?>
							<th><?= $field; ?></th>
						<?php } ?>
						<th colspan = "2">Управление</th>
					</tr>
				</thead>
				<tbody>
					<?php foreach ($items as $item) { ?>
					    <tr>
							<?php foreach ($fields as $key => $field) { ?>
								<td>
									<?= $item[$key]; ?>
								</td>
							<?php } ?>
							<td><?= $editor->update->GetLink('Изменить'); ?></td>
							<td><?= $editor->delete->GetLink('Удалить'); ?></td>
						</tr>
					<?php } ?>
				</tbody>
			</table>
		<?php }

	}