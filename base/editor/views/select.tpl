<?php

	namespace Base\Templates\Editor;

	use Base\Editor\Editor;
	use Base\Templates\View;

	class Select extends View {

		public function ToVar(Editor $editor, array $fields, array $items, string $title): string {
			$this->Start();
			$this->Render($editor, $fields, $items, $title);
			return $this->Read();
		}

		public function Render(Editor $editor, array $fields, array $items, string $title) {
			$col = count($editor->manage);
		?>
			<div class = "navigate">
				<?php foreach ($editor->navigateSelect as $navigate) echo $navigate($editor->params); ?>
			</div>
			<h1><?= $title; ?></h1>
			<table class = "select">
				<thead>
					<tr>
						<?php foreach ($fields as $field) { ?>
							<th><?= $field; ?></th>
						<?php } ?>
						<?php if ($col) { ?><th colspan = "<?= $col ?>">Управление</th><?php } ?>
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
							<?php foreach ($editor->manage as $manage) { ?>
								<td><?= $manage($editor->params, $item); ?></td>
							<?php } ?>
						</tr>
					<?php } ?>
				</tbody>
			</table>
		<?php }

	}