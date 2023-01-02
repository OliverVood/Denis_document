<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;

	class Main extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "view general main">
				<div><a href = "/estimate">Смета</a></div>
				<div><a href = "/certificate">Акт выполненых работ</a></div>
			</div>
		<?php }

	}