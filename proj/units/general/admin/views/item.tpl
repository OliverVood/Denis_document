<?php

	namespace Proj\Admin\Templates\General;

	use Base\Templates\View;

	class Item extends View {

		public function ToVar(string $item): string {
			$this->Start();
			$this->Render($item);
			return $this->Read();
		}

		public function Render(string $item) { ?>
			<li><?= $item; ?></li>
		<?php }

	}