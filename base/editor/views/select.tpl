<?php

	namespace Base\Templates\Editor;

	use Base\Templates\View;

	class Select extends View {

		public function ToVar(array $fields, array $items, string $title): string {
			$this->Start();
			$this->Render($fields, $items, $title);
			return $this->Read();
		}

		public function Render(array $fields, array $items, string $title) { ?>
			<h1><?= $title; ?></h1>
			<table>
				<thead>
					<tr>
						<?php foreach ($fields as $field) { ?>
							<th><?= $field; ?></th>
						<?php } ?>
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
						</tr>
					<?php } ?>
				</tbody>
			</table>
		<?php }

	}