<?php

	namespace Proj\Admin\Templates\General;

	require 'item.tpl';

	use Base\Templates\View;

	class Group extends View {

		public function ToVar(string $title, array $items): string {
			$this->Start();
			$this->Render($title, $items);
			return $this->Read();
		}

		public function Render(string $title, array $items) { ?>
			<li>
				<span>
					<?= $title; ?>
					<ul>
						<?php foreach ($items as $item) { Item::object()->Render($item); } ?>
					</ul>
				</span>
			</li>
		<?php }

	}